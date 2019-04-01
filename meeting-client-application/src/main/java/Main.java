import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Screen;
import javafx.stage.Stage;

public class Main extends Application {


    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        Rectangle2D primScreenBounds = Screen.getPrimary().getVisualBounds();
        Stage loginStage = new Stage();

        loadStage(loginStage, "/fxml/LoginWindow.fxml", "meeTINg Client Application");
        loginStage.show();
        loginStage.setX((primScreenBounds.getWidth()/2 - loginStage.getWidth()) / 2);
        loginStage.setY((primScreenBounds.getHeight() - loginStage.getHeight()) / 2);
    }

    private void loadStage(Stage stage, String resourcePath, String title)
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource(resourcePath));
            AnchorPane root = fxmlLoader.load();
            Scene scene = new Scene(root);
            stage.setScene(scene);
            stage.setTitle(title);
            stage.setResizable(false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
