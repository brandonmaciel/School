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

public class problem2 extends Application
{
   private TextField propertyTextField;
   private Label assessmentLabel;
   private Label propTaxLabel;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   @Override
   public void start(Stage primaryStage)
   {
      Label whosaleLabel = new Label("Enter the value of the property:");
      
      propertyTextField = new TextField();
      
      Button calcButton = new Button("Calculate Assessment and Taxes");
      calcButton.setOnAction(new CalcButtonHandler());
      assessmentLabel = new Label();
      propTaxLabel = new Label();
      
      HBox hbox = new HBox(10, whosaleLabel, propertyTextField);
      
      VBox vbox = new VBox(10, hbox, calcButton, assessmentLabel, propTaxLabel);
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
         // Get the property value.
         Double propertyValue = Double.parseDouble(propertyTextField.getText());

         // Calculate assessment value
         Double assessmentValue = propertyValue * 0.60;

         // Calculate property taxes
         Double propTaxes = (assessmentValue/100) * 0.64;
         
         // Display the results.
         assessmentLabel.setText(String.format("Assessment price of property: $%,.2f", assessmentValue));
         propTaxLabel.setText(String.format("Property Taxes: $%,.2f", propTaxes));
      }
   }
}