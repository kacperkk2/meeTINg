package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;

public class EventsWindowController {

    @FXML
    public Button createButton;

    @FXML
    public Button refreshButton;

    @FXML
    public Button returnButton;

    @FXML
    public Button signOutButton;

    @FXML
    public ListView eventList;

    @FXML
    public void signOutClicked(ActionEvent actionEvent) {
        System.out.println("signOutClicked");
    }

    @FXML
    public void returnClicked(ActionEvent actionEvent) {
        System.out.println("returnClicked");
    }

    @FXML
    public void refreshClicked(ActionEvent actionEvent) {
        System.out.println("refreshClicked");
    }

    @FXML
    public void createClicked(ActionEvent actionEvent) {
        System.out.println("createClicked");
    }

    @FXML
    public void eventClicked(MouseEvent mouseEvent) {
        System.out.println("eventClicked");
    }
}
