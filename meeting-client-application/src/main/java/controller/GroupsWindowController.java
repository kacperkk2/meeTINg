package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import model.Group;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class GroupsWindowController {

    @FXML ListView<Group> listView;
    @FXML Button createButton;
    @FXML Button requestsButton;

    private Group pickedGroup;
    private List<Group> groups;

    // na refresh powinno isc od klienta do serwa zapytanie o wszystkie grupy, to samo jak przy wejsciu do groupsview
    // i pozniej od nowa odpalic loadGroups

    @FXML
    public void initialize() {
        // jesli ktos nie jest leader to trzeba buttons disable
        int leader = 0;
        if(leader == 0) {
            createButton.setDisable(true);
            requestsButton.setDisable(true);
        }

        // imitacja zwracanego responsa, domyslnie raczej bedzie od np loginwindow wolac setera i ustawiac grupy
        Group g1 = new Group();
        g1.setId(1);
        g1.setName("Jakas grupa");
        Group g2 = new Group();
        g2.setId(2);
        g2.setName("Super grupa na tiny");
        groups = new ArrayList<>();
        groups.addAll(Arrays.asList(g1, g2));

        refreshClicked();
    }

    @FXML
    private void listClicked(){
        // albo po kliknieciu przerzucac do grupy albo dac buttona ktory klika enter picked group

        // warunek zeby po kliknieciu w puste pola sie nie wywolywalo i zeby po kliknieciu w puste pole nie odpalalo sie dla biezacego pickedGroup
        if(listView.getSelectionModel().getSelectedItem() != null
                && listView.getSelectionModel().getSelectedItem() != pickedGroup) {
            pickedGroup = listView.getSelectionModel().getSelectedItem();

            System.out.println(pickedGroup.toString());
        }
    }

    @FXML
    private void signOutClicked(ActionEvent event){

        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Confirmation Dialog");
        alert.setHeaderText("Are you sure??");

        Optional<ButtonType> result = alert.showAndWait();
        if (result.get() == ButtonType.OK){
            try {
                FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/LoginWindow.fxml"));
                AnchorPane root = fxmlLoader.load();
                Scene scene = new Scene(root);
                Stage userMainStage = (Stage)((Node) event.getSource()).getScene().getWindow();

                userMainStage.setScene(scene);
                userMainStage.show();
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void refreshClicked() {
        // daje requesta i jako odpowiedz przypisuje dostana liste grup do groups
        // cos ala groups = sendRequest(cos tam);
        // jak juz ja mam to wrzucam
        listView.getItems().clear();
        listView.getItems().addAll(groups);

        System.out.println("refresh!");
    }

}
