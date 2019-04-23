package meeting;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class StageLoader {

    public static void loadStage(Stage stage, FXMLLoader fxmlLoader)
    {
        try {
            AnchorPane root = fxmlLoader.load();
            Scene scene = new Scene(root);
            scene.getStylesheets().addAll(Main.class.getResource("/css/background.css").toExternalForm());

            stage.setScene(scene);
            stage.setTitle("meeTINg Client Application");
            stage.setResizable(false);
            stage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
