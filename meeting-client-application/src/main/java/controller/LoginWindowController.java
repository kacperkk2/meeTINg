package controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class LoginWindowController {

    @FXML
    public void logging() {
        System.out.println("logging");
    }

    @FXML
    public void registration() {
        Stage loginStage = new Stage();

        loadStage(loginStage, "/fxml/RegistrationWindow.fxml", "meeTINg Registration");
        loginStage.show();
        loginStage.setWidth(640);
        loginStage.setHeight(480);
        loginStage.setX(300);
        loginStage.setY(300);
    }

    private void loadStage(Stage stage, String resourcePath, String title)
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(LoginWindowController.class.getResource(resourcePath));
            AnchorPane root = fxmlLoader.load();
            root.setId("userLogin");
            Scene scene = new Scene(root);
            scene.getStylesheets().addAll(this.getClass().getResource("../../resources/css/background.css").toExternalForm());
            stage.setScene(scene);
            stage.setTitle(title);
            stage.setResizable(false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
