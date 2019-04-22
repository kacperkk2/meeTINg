package controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import model.Group;

import static enums.SystemRole.USER;

public class EventsWindowController {

    @FXML public Button createButton;
    @FXML public Button refreshButton;
    @FXML public Button returnButton;
    @FXML public Button signOutButton;
    @FXML public ListView eventList;

    private Group pickedGroup;

    @FXML
    public void initialize() {
            // TODO inicjalizacja listy eventow, tak jak w groupwindow
            // TODO u siebie musisz zrobic inicjalizacje eventow, tak jak inicjalizacja grup nie jest w login tylko w groupwindow
            refreshClicked();
    }

    @FXML
    public void signOutClicked(ActionEvent actionEvent) {
        System.out.println("signOutClicked");
    }

    @FXML
    public void returnClicked(ActionEvent actionEvent) {
        System.out.println("returnClicked");
    }

    @FXML
    public void refreshClicked() {
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

    public void setPickedGroup(Group pickedGroup) {
        this.pickedGroup = pickedGroup;
    }
}
