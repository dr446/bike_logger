import controlP5.*;
import grafica.*;
String[] lines;
int index=0;
String[] list;
float x;
float y;

ControlP5 cp5;
DropdownList d1;
int cnt = 0;

void setup() {
  size(1000, 800);
  background(215,215,255);
  
  // load in data in from csv file
  lines = loadStrings("mock_SD_data.csv");

  // Prepare the points for the plot
  int numberofPoints = lines.length;
  GPointsArray points = new GPointsArray(numberofPoints);

  // Create a new plot and set its position on the screen
  GPlot plot = new GPlot(this);
  plot.setPos(1, 25);
  // or all in one go
  // GPlot plot = new GPlot(this, 25, 25);
  
  for (int i = 0; i < numberofPoints; i++) {
    list = split(lines[i], ',');
    x=float(list[0]);
    y=float(list[1]);
    ///points.add(x, y);
    plot.addPoint(x,y);
  }
  
  //drop down list stuff
  cp5 = new ControlP5(this);
  // create a DropdownList, 
  d1 = cp5.addDropdownList("myList-d1")
          .setPosition(550, 100)
          ;
          
  customize(d1); // customize the first list
 
  
  

  // Set the plot title and the axis labels
  plot.setTitleText("Mock csv data");
  plot.getXAxis().setAxisLabelText("x axis");
  plot.getYAxis().setAxisLabelText("y axis");

  
  // Draw the plot  
  plot.beginDraw();
  plot.drawBackground();
  plot.drawBox();
  plot.drawXAxis();
  plot.drawYAxis();
  plot.drawTitle();
  plot.drawGridLines(GPlot.BOTH);
  plot.drawLines();
  
  plot.endDraw();
}





void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
  ddl.setBackgroundColor(color(0));
  ddl.setItemHeight(20);
  ddl.setBarHeight(15);
  ddl.getCaptionLabel().set("Select Graph To View");
  
  ddl.addItem("Speed Graph",0);
  ddl.addItem("Some Other Graph",1);
  
  //ddl.scroll(0);
  ddl.setColorBackground(color(200));
  ddl.setColorActive(color(255, 128));
}

 
 void controlEvent(ControlEvent theEvent) {
  // DropdownList is of type ControlGroup.
  // A controlEvent will be triggered from inside the ControlGroup class.
  // therefore you need to check the originator of the Event with
  // if (theEvent.isGroup())
  // to avoid an error message thrown by controlP5.

  if (theEvent.isGroup()) {
    // check if the Event was triggered from a ControlGroup
    println("event from group : "+theEvent.getGroup().getValue()+" from "+theEvent.getGroup());
  } 
  else if (theEvent.isController()) {
    println("event from controller : "+theEvent.getController().getValue()+" from "+theEvent.getController());
  }
}


void draw() {
  background(128);
}
