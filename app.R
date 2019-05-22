library(shiny)
library(tidyverse)
library(gridExtra)
library(grid)
library(shinyalert)
source("Game_Implementation.R")


# Define UI for application that draws a histogram
ui <- fluidPage(
  useShinyalert(), 
  # Application title
  titlePanel("Camel Up"),
  
  # Sidebar with a slider input for number of bins 
  sidebarLayout(
    sidebarPanel(
      radioButtons("buttons", "Move Type",
                   c("Move Camel","Place Leg Bet","Place Tile","Place Overall Bet"),
                   selected = "Move Camel"),
      conditionalPanel(condition = "input.buttons == 'Place Leg Bet'",
                       selectInput('legbetcolor',
                                   "Camel Color:",
                                   c("","Yellow","Orange","Blue","Green","White"))
      ),
      conditionalPanel(condition = "input.buttons == 'Place Tile'",
                       selectInput('tiletype',
                                   "Tile Type",
                                   c("","Plus","Minus")),
                       selectInput('tilespace',
                                   "Space Number:",
                                   c("", 1:16))
      ),
      conditionalPanel(condition = "input.buttons == 'Place Overall Bet'",
                       selectInput('overallbettype',
                                   "Bet Type",
                                   c("","Winner", "Loser")),
                       selectInput('overallbetcolor',
                                   "Camel Color:",
                                   c("","Yellow","Orange","Blue","Green","White"))
      ),
      
      actionButton('submit',
                   "Go!"),
      textOutput("currentTurn"),
      #selectInput("player", "Select Player", c("player 1", "player 2")),
      uiOutput("playerName"),
      textInput("newName", "Enter New Name"),
      actionButton("changeName", "Change Name")
    ),
    
    # Show a plot of the generated distribution
    mainPanel(
      tabsetPanel(type = "tabs",
                  tabPanel("View Game", 
                           plotOutput("board"),
                           tableOutput("gameData"),
                           tableOutput("playerData"),
                           tableOutput("betData"),
                           tableOutput("diceLeft"),
                           textOutput("moveResult")),
                  tabPanel("View Sim",
                           selectInput("simColor", "Color:",
                                       c("Blue", "Green", "Orange", "White", "Yellow")),
                           selectInput("simMove", "Move Type",
                                       c("Move Camel","Place Leg Bet","Place Tile","Place Overall Bet"),
                                       selected = "Move Camel"),
                           sliderInput("nSims", "Select Number of Simulations",
                                       min = 1, max = 1000, value = 500),
                           actionButton('Sim',
                                        "Simulate!"),
                           conditionalPanel(condition = "input.simMove == 'Place Leg Bet'",
                                            selectInput('legbetcolorSim',
                                                        "Camel Color:",
                                                        c("","Yellow","Orange","Blue","Green","White"))
                           ),
                           conditionalPanel(condition = "input.simMove == 'Place Tile'",
                                            selectInput('tiletypeSim',
                                                        "Tile Type",
                                                        c("","Plus","Minus")),
                                            selectInput('tilespaceSim',
                                                        "Space Number:",
                                                        c("", 1:16))
                           ),
                           conditionalPanel(condition = "input.simMove == 'Place Overall Bet'",
                                            selectInput('overallbettypeSim',
                                                        "Bet Type",
                                                        c("","Winner", "Loser")),
                                            selectInput('overallbetcolorSim',
                                                        "Camel Color:",
                                                        c("","Yellow","Orange","Blue","Green","White"))
                           ),
                           checkboxGroupInput("vLinesBool", "Show Standard Deviations:", c("Mean" = TRUE,
                                                                                           "1 SD" = TRUE,
                                                                                           "2 SD" = TRUE)),
                           plotOutput("stackSims")),
                  tabPanel("Custom Game",
                           div(style="display: inline-block;vertical-align:top; width: 150px;",actionButton("clearBoard",
                                                                                                            "Clear Board"),
                               # div(style="display: inline-block;vertical-align:top; width: 100px;",HTML("<br>")),
                               div(style="display: inline-block;vertical-align:top; width: 150px;",actionButton(inputId="customCopy", label="Copy Board"))),
                           selectInput("customType", "Select Object to Add to the Board", c("Camel", "Tile")),
                           conditionalPanel(condition = "input.customType == 'Camel'",
                                            selectInput("customSpace", "Space",
                                                        1:19),
                                            selectInput("customColor","Color:",
                                                        c("Blue", "Green", "Orange", "White", "Yellow")),
                                            
                                            selectInput("customBets", "Bets Remaining",
                                                        0:3),
                                            checkboxInput("customDie", "Add Die")),
                           conditionalPanel(condition = "input.customType == 'Tile'",
                                            #selectInput("Test", "Test", 1:5)),
                                            selectInput("customTileType", "Select Tile Type:",
                                                        c("Plus", "Minus")),
                                            uiOutput("customTileSpace")),
                           
                           actionButton("createCustom",
                                        "Enter!"),
                           plotOutput("customGameGraph"),
                           tableOutput("customTable"),
                           tableOutput("customPlayerData"),
                           tableOutput("customBetData"),
                           tableOutput("customDiceLeft"))
      )
    )
    
  )
)


#x[[1]][x[[2]] == ""]

# Define server logic required to draw a histogram
server <- function(input, output) {
  nPlayers <- NULL
  nPlayers <- shinyalert(title = "input number of players", 
                         type = "input",
                         callbackR = function(nPlayers) { 
                           print(nPlayers)
                           nPlayers <- as.numeric(nPlayers)
                           # players <- NULL
                           # shiny::validate(
                           #   need(!is.null(nPlayers), "simTurnString blank")
                           # )
                           # players <- shinyalert(title = "input player 1 name", type = "input")
                           # s <- system$new(4, players = c("Michael", "Tom", "Alex", "Tina"), isDup = TRUE)
                           # variables <- reactiveValues("game" = s,
                           #                             "custom" = game$duplicate)
                           players <- paste(rep("Player", nPlayers), 1:nPlayers)
                           print("players made")
                           
                           game <- system$new(nPlayers, players = players, isDup = TRUE)
                           print("game created")
                           variables <- reactiveValues(customDiceLeft = game$createDiceTable(),
                                                       players = paste(rep("Player", nPlayers), 1:nPlayers),
                                                       tiles = game$board$getTileSpaces())
                           
                           output$playerName <- renderUI({
                             selectInput("player", "Select Player", variables$players)
                             
                           })
                           
                           
                           
                           output$board <- renderPlot({
                             game$graphGame()
                           })
                           output$currentTurn <- renderText({
                             paste0("It is currently ", game$players[[1]]$name, "'s turn.")
                           })
                           
                           observeEvent(input$changeName, {
                             game$changeName(input$player, input$newName)
                             output$board <- renderPlot({
                               game$graphGame()
                             })
                             output$playerData <- renderTable({
                               game$purseTable()
                             }, caption = "Purse Table",
                             caption.placement = getOption("xtable.caption.placement", "top"))
                             variables$players <- game$playersNames()
                           })
                           
                           observeEvent(input$submit, {
                             if(input$buttons == 'Move Camel'){
                               turnString <- "move"
                             }
                             else if(input$buttons == 'Place Leg Bet'){
                               turnString <- paste(c("bet", input$legbetcolor), collapse = " ")
                             }
                             else if(input$buttons == 'Place Tile'){
                               if(input$tiletype == 'Plus'){
                                 turnString <- paste(c("plus", input$tilespace), collapse = ' ')
                               }
                               else if(input$tiletype == 'Minus'){
                                 turnString <- paste(c('minus', input$tilespace), collapse = " ")
                               }
                             }
                             else if(input$buttons == 'Place Overall Bet'){
                               if(input$overallbettype == 'Winner'){
                                 turnString <- paste(c("winner", input$overallbetcolor), collapse = " ")
                               }
                               else if(input$overallbettype == "Loser"){
                                 turnString <- paste(c('loser', input$overallbetcolor), collapse = ' ')
                               }
                               
                             }
                             
                             
                             output$moveResult <- renderText({
                               game$take.turn(turnString)
                             })
                             
                             output$currentTurn <- renderText({
                               paste0("It is currently ", game$players[[game$current.player]]$name, "'s turn.")
                             })
                             
                             output$board <- renderPlot({
                               game$graphGame()
                             })
                             output$diceLeft <- renderTable({
                               game$createDiceTable()
                             })
                             
                             variables$tiles <- game$board$getTileSpaces()
                             output$customTileSpace <-  renderUI({
                               temp <- variables$tiles
                               print(variables$tiles[[1]])
                               selectInput("customTileSpaceInput", "Select Space", variables$tiles[[1]])
                             })
                             
                             output$betData <- renderTable({
                               game$createBetsTable()
                             }, caption = "Bets Table",
                             caption.placement = getOption("xtable.caption.placement", "top"))
                             
                             output$playerData <- renderTable({
                               game$purseTable()
                             }, caption = "Purse Table",
                             caption.placement = getOption("xtable.caption.placement", "top"))
                             
                             
                             
                           })
                           
                           simTurnString <- eventReactive(input$Sim, {
                             if(input$simMove == 'Move Camel'){
                               "move"
                             }
                             else if(input$simMove == 'Place Leg Bet'){
                               paste(c("bet", input$legbetcolorSim), collapse = " ")
                             }
                             else if(input$simMove == 'Place Tile'){
                               if(input$tiletypeSim == 'Plus'){
                                 paste(c("plus", input$tilespaceSim), collapse = ' ')
                               }
                               else if(input$tiletypeSim == 'Minus'){
                                 paste(c('minus', input$tilespaceSim), collapse = " ")
                               }
                             }
                             else if(input$simMove == 'Place Overall Bet'){
                               if(input$overallbettypeSim == 'Winner'){
                                 paste(c("winner", input$overallbetcolorSim), collapse = " ")
                               }
                               else if(input$overallbettypeSim == "Loser"){
                                 paste(c('loser', input$overallbetcolorSim), collapse = ' ')
                               }
                             }
                             #game$simNGames(simTurnString(), input$nSims)
                           })
                           
                           observeEvent(input$Sim, {
                             game$simNGames(simTurnString(), input$nSims)
                           })
                           
                           
                           output$playerData <- renderTable({
                             game$purseTable()
                           }, caption = "Purse Table",
                           caption.placement = getOption("xtable.caption.placement", "top"))
                           
                           
                           output$diceLeft <- renderTable({
                             game$createDiceTable()
                           })
                           
                           output$betData <- renderTable({
                             game$createBetsTable()
                           }, caption = "Bets Table",
                           caption.placement = getOption("xtable.caption.placement", "top"))
                           
                           output$stackSims <- renderPlot({
                             shiny::validate(
                               need(simTurnString() != "", "Error: simTurnString blank")
                             )
                             print(simTurnString())
                             #game$createSimGraphs(input$simColor, simTurnString(), 500)
                             print("print(input$vLinesBool)")
                             # print(input$vLinesBool) ####################################
                             game$createSimGraphs(input$simColor, simTurnString(), input$nSims, input$vLinesBool) #####HERE
                           })
                           
                           observeEvent(input$clearBoard, {
                             print("test")
                             game$clearBoard()
                             output$customGameGraph <- renderPlot({
                               game$graphGame()
                             })
                           })
                           
                           # observeEvent(input$createCustom, {
                           output$customGameGraph <- renderPlot({
                             game$graphGame()
                           })
                           
                           observeEvent(input$createCustom, {
                             print("adding custom camel")
                             #game$changeCamel(input$color, color$space)
                             print(input$customColor)
                             print(input$customSpace)
                             print(input$customDie)
                             print(typeof(input$customDie))
                             print(class(input$customDie))
                             
                             if(input$customType == "Camel"){
                               rept <- FALSE
                               colors <- NULL
                               if(length(game$board$tot.camels) > 0){
                                 for(i in 1:length(game$board$tot.camels)){
                                   colors <- c(game$board$tot.camels[[i]]$color, colors)
                                 }
                               }
                               rept <- input$customColor %in% colors
                               
                               if(!rept){
                                 game$changeCamel(input$customColor, as.integer(input$customSpace))
                                 game$changeBets(input$customColor, as.integer(input$customBets))
                                 game$changeDie(color = input$customColor, input$customDie)
                                 # output$customDiceLeft <- renderTable({
                                 #   game$createDiceTable()
                                 # })
                                 
                                 variables$customDiceLeft <- game$createDiceTable()
                                 output$customGameGraph <- renderPlot({
                                   game$graphGame()
                                 })
                                 output$customTable <- renderTable({
                                   game$initial_record()
                                 })
                                 output$customPlayerData <- renderTable({
                                   game$purseTable()
                                 })
                                 output$customBetData <- renderTable({
                                   game$createBetsTable()
                                 })
                               }
                             } else { #input$customType == "Tile
                               print("placing tile")
                               game$placeTile(input$customTileType, as.numeric(input$customTileSpace), "Player 1")
                             }
                             
                             variables$tiles <- game$board$getTileSpaces()
                             
                           })
                           
                           observeEvent(input$customType, {
                             variables$tiles <- game$board$getTileSpaces()
                           })
                           
                           
                           output$customPlayerData <- renderTable({
                             game$purseTable()
                           })
                           output$customBetData <- renderTable({
                             game$createBetsTable()
                           })
                           # output$customDiceLeft <- renderTable({
                           #   game$createDiceTable()
                           # })
                           output$customDiceLeft <- renderTable({
                             variables$customDiceLeft
                           })
                           
                           
                           output$customTable <- renderTable({
                             game$initial_record()
                           })
                           
                           observeEvent(input$customCopy,{
                             output$customGameGraph <- renderPlot({
                               game$graphGame()
                             })
                             output$board <- renderPlot({
                               game$graphGame()
                             })
                             
                             output$currentTurn <- renderText({
                               paste0("It is currently ", game$players[[(game$current.player + 1) %% game$n.players]]$name, "'s turn.")
                             })
                             
                             output$board <- renderPlot({
                               game$graphGame()
                             })
                             output$diceLeft <- renderTable({
                               game$createDiceTable()
                             })
                             
                             output$betData <- renderTable({
                               game$createBetsTable()
                             }, caption = "Bets Table",
                             caption.placement = getOption("xtable.caption.placement", "top"))
                             
                             output$playerData <- renderTable({
                               game$purseTable()
                             }, caption = "Purse Table",
                             caption.placement = getOption("xtable.caption.placement", "top"))
                           })
                           
                           
                           # })
                           # stack <- s$graphCamelSim(input$simColor, "move", 500, type = "stack")
                           # space <- s$graphCamelSim(input$simColor, "move", 500, type = "space")
                           # pushViewport(viewport(layout = grid.layout(2, 1), xscale = c(0,19)))
                           # print(space, vp = viewport(layout.pos.row = 2, layout.pos.col=1))
                           # print(stack, vp = viewport(layout.pos.row = 1, layout.pos.col=1))
                         })
}

# Run the application 
shinyApp(ui = ui, server = server)


# splitLayout(
#  actionButton("move",
#              "Move Camel", width = '100%'),
#  actionButton('legbet',
#               "Place Leg Bet", width = '100%')
# ),
# splitLayout(
#  actionButton('tile',
#               "Place Tile", width = '100%'),
#  actionButton('overallbet',
#               "Place Overall Bet", width = '100%')
# ),
# conditionalPanel(condition = "input.legbet%2 == 1",
#                  selectInput('legbetcolor',
#                              "Camel Color:",
#                              c("","Yellow","Orange","Blue","Green","White"))
# ),
# conditionalPanel(condition = "input.tile%2 == 1",
#                  selectInput('tilespace',
#                              "Space Number:",
#                              c(1:16))
# ),
# conditionalPanel(condition = "input.overallbet%2 == 1",
#                  selectInput('overallbetcolor',
#                              "Camel Color:",
#                              c("","Yellow","Orange","Blue","Green","White"))
# ),
