import controller.LoginWindowController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Screen;
import javafx.stage.Stage;
import client.Client;


public class Main extends Application {

    private Client client;

    public static void main(String[] args) {
        launch(args);
    }

    public void initClient() {
        client = new Client();
    }

    @Override
    public void start(Stage primaryStage) {
        initClient();

        Rectangle2D primScreenBounds = Screen.getPrimary().getVisualBounds();
        Stage loginStage = new Stage();

        loadStage(loginStage, "/fxml/LoginWindow.fxml", "meeTINg Client Application");
        loginStage.show();
    }

    private void loadStage(Stage stage, String resourcePath, String title)
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource(resourcePath));
            AnchorPane root = fxmlLoader.load();
            //root.setId("userLogin");
            Scene scene = new Scene(root);
            scene.getStylesheets().addAll(this.getClass().getResource("css/background.css").toExternalForm());

            LoginWindowController loginWindowController = fxmlLoader.getController();
            loginWindowController.setClient(client);

            stage.setScene(scene);
            stage.setTitle(title);
            stage.setResizable(false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
