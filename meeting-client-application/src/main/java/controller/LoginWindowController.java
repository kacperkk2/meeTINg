package controller;

import client.Client;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;


public class LoginWindowController {

    private Client client;

    @FXML TextField usernameField;
    @FXML PasswordField passwordField;

    @FXML
    public void signInClicked(ActionEvent event) {

        // te pola username i haslo to musza byc pola obiektu user
        //                                    a tu musi byc json w stringu
        String response = client.sendRequestRecResponse(usernameField.getText() + passwordField.getText());

        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/GroupsWindow.fxml"));
            AnchorPane root = fxmlLoader.load();
            Scene scene = new Scene(root);
            Stage userMainStage = (Stage)((Node) event.getSource()).getScene().getWindow();

            userMainStage.setScene(scene);
            userMainStage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void registration(ActionEvent event) {


        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/RegistrationWindow.fxml"));
            AnchorPane root = fxmlLoader.load();
            Scene scene = new Scene(root);
            Stage userMainStage = (Stage)((Node) event.getSource()).getScene().getWindow();

            userMainStage.setScene(scene);
            userMainStage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

//    private void loadStage(Stage stage, String resourcePath, String title)
//    {
//        try {
//            FXMLLoader fxmlLoader = new FXMLLoader(LoginWindowController.class.getResource(resourcePath));
//            AnchorPane root = fxmlLoader.load();
//            root.setId("userLogin");
//            Scene scene = new Scene(root);
//            scene.getStylesheets().addAll(this.getClass().getResource("../../resources/css/background.css").toExternalForm());
//            stage.setScene(scene);
//            stage.setTitle(title);
//            stage.setResizable(false);
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//    }

    public void setClient(Client client) {
        this.client = client;
    }
}
