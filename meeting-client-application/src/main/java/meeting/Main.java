package meeting;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;


public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        FXMLLoader fxmlLoader = new FXMLLoader(this.getClass().getResource("/fxml/LoginWindow.fxml"));
        StageLoader.loadStage(new Stage(), fxmlLoader);
    }
}
