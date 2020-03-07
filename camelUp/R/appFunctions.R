camelScale <- function(){
  colors <- c("darkgreen", "blue", "yellow", "white", "orange")
  values <- c("Green", "Blue", "Yellow", "White", "Orange")
  names(colors) <- values

  return(scale_fill_manual(name = "Color",values = colors))
}

makeBoardGraph <- function(gameObj){
  plt <- gameObj$getCamelDF() %>%
    ggplot(aes(x = Space, y = Height, fill = Color)) +
    geom_tile(color = "black", size = 1) +
    ggplot2::coord_cartesian(xlim = c(1, 19), ylim = c(0.5,5.49)) +
    ggplot2::scale_x_continuous(breaks = 1:19) +
    ggplot2::scale_y_continuous(labels = c("0.00", "1.00", "2.00", "3.00", "4.00", "5.00"),
                                breaks = 0:5) +
    theme_classic() +
    camelScale()

  return(plt)
}


generateUI <- function(){
  ui <- fluidPage(
    titlePanel("Camel Up"),
    mainPanel(
      tabsetPanel(type = "tabs",
                  tabPanel("View Game",
                           plotOutput("gameBoard"),
                           fluidRow(
                             column(width = 4, tableOutput("positionDF")),
                             column(width = 4, tableOutput("legBetDF"))
                           )


                  ))
    )
  )

  return(ui)

}

server <- function(input, output){
  gamePlay <- Game$new(19, 3, TRUE)
  output$gameBoard <- renderPlot(makeBoardGraph(gamePlay))
  output$positionDF <- renderTable(gamePlay$getCamelDF() %>% arrange(-Space, -Height))
  output$legBetDF <- renderTable(gamePlay$getLegBetDF())
}

shinyApp(ui = generateUI(), server = server)
