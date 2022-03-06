import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.Button;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;

public class MarkupCalc extends Application
{
   private TextField wholesaleTextField;
   private TextField markupTextField;
   private Label retailLabel;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   @Override
   public void start(Stage primaryStage)
   {
      Label whosaleLabel = new Label("Enter the price of the item:");
      Label markupLabel = new Label("Enter the markup percentage:");
      
      wholesaleTextField = new TextField();
      markupTextField = new TextField();
      
      Button calcButton = new Button("Calculate retail price");
      calcButton.setOnAction(new CalcButtonHandler());
      retailLabel = new Label();
      
      HBox hbox = new HBox(10, whosaleLabel, wholesaleTextField);
      HBox hbox2 = new HBox(10, markupLabel, markupTextField);
      
      VBox vbox = new VBox(10, hbox, hbox2, calcButton, retailLabel);
      vbox.setAlignment(Pos.CENTER);
      vbox.setPadding(new Insets(10));

      Scene scene = new Scene(vbox);
      primaryStage.setScene(scene);
      primaryStage.setTitle("Retail Price Calculator");
      primaryStage.show();   
   }
    
   class CalcButtonHandler implements EventHandler<ActionEvent>
   {
      @Override
      public void handle(ActionEvent event)
      {
         // Get the whosalePrice.
         Double whosalePrice = Double.parseDouble(wholesaleTextField.getText());
         
         // Get the mark up.
         Double markup = Double.parseDouble(markupTextField.getText());

         // Calculate retail price
         Double retailPrice = whosalePrice * (1 + markup/100);
         
         // Display the results.
         retailLabel.setText(String.format("The retail price of the item is $%,.2f", retailPrice));
      }
   }
}