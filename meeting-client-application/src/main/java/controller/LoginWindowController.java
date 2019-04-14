package controller;

import client.Client;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import controller.GroupsWindowController;

import java.awt.*;

public class LoginWindowController {

    private Client client;

    @FXML
    public void signInClicked(ActionEvent event) {

        // dodac ladowanie do wiadomosci tresci pola na login i haslo i przesylac wiadomosc z tym do serwa
        client.sendMessage();

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

    public void setClient(Client client) {
        this.client = client;
    }
}
