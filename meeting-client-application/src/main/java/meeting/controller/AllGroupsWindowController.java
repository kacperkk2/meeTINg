package meeting.controller;

import javafx.scene.control.*;
import meeting.StageLoader;
import meeting.api.request.GroupListRequest;
import meeting.api.request.MembershipRequest;
import meeting.api.request.NewGroupRequest;
import meeting.api.response.ErrorResponse;
import meeting.api.response.GroupListResponse;
import meeting.api.response.NewGroupResponse;
import meeting.client.Client;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import meeting.enums.RequestFlag;
import meeting.enums.ResponseFlag;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.stage.Stage;
import meeting.model.Group;
import meeting.model.User;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static meeting.enums.SystemRole.USER;


public class AllGroupsWindowController {

    @FXML ListView<Group> listView;
    @FXML Button applyButton;
    @FXML Label roleInfoLabel;

    private Group pickedGroup;
    private Client client;
    private User user;

    @FXML
    public void initialize() {

        applyButton.setDisable(true);

        Platform.runLater(() ->{
            if(user.getSystemRole() == USER) {
                roleInfoLabel.setText("Logged as User (limited options)");
            }

            refreshClicked();
        });
    }

    @FXML
    private void applyClicked() {

        // robie JSONa
        GsonBuilder builder = new GsonBuilder();
        builder.setPrettyPrinting();
        Gson gson = builder.create();

        MembershipRequest membershipRequest = MembershipRequest.builder()
                .userId(user.getId())
                .groupId(pickedGroup.getId())
                .build();

        String requestString = RequestFlag.MEMBREQ.toString() + gson.toJson(membershipRequest);

//        String membershipResponseString = meeting.client.sendRequestRecResponse(requestString);

        // symulacja poprawnego
        String membershipResponseString = ResponseFlag.MEMBREQ.toString();

        if(membershipResponseString.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            ErrorResponse errorResponse = gson.fromJson(membershipResponseString.substring(7), ErrorResponse.class);
            showErrorAlert(errorResponse.getMessage());
            return;
        }

        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Information Dialog");
        alert.setHeaderText("Membership request send to leader of group");
        alert.showAndWait();

        // zeby po aplikowaniu uzytkownika nie pokazala mu sie znow ta sama grupa zeby nie mogl w nia kliknac
        refreshClicked();
    }

    @FXML
    private void returnClicked(Event event) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/GroupsWindow.fxml"));
            StageLoader.loadStage((Stage)((Node) event.getSource()).getScene().getWindow(), fxmlLoader);
            GroupsWindowController groupsWindowController = fxmlLoader.getController();
            groupsWindowController.setClient(client);
            groupsWindowController.setUser(user);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void listClicked(){
        // warunek zeby po kliknieciu w puste pola sie nie wywolywalo i zeby po kliknieciu w puste pole nie odpalalo sie dla biezacego pickedGroup
        if(listView.getSelectionModel().getSelectedItem() != null &&
                listView.getSelectionModel().getSelectedItem() != pickedGroup) {

            pickedGroup = listView.getSelectionModel().getSelectedItem();
            applyButton.setDisable(false);
        }
    }

    @FXML
    private void signOutClicked(ActionEvent event) {

        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setHeaderText(null);
        alert.setContentText("Do you want to sign out?");

        Optional<ButtonType> result = alert.showAndWait();
        if(result.isPresent()){
            ButtonType reloadedResult = result.get();
            if (reloadedResult == ButtonType.OK){
                try {
                    FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/LoginWindow.fxml"));
                    StageLoader.loadStage((Stage)((Node) event.getSource()).getScene().getWindow(), fxmlLoader);

                    // TODO dac ustawianie clienta jak tomek juz ogarnie
                } catch(Exception e) {
                    e.printStackTrace();
                }
            }
        }

    }

    @FXML
    private void refreshClicked() {
        // robie JSONa
        GsonBuilder builder = new GsonBuilder();
        builder.setPrettyPrinting();
        Gson gson = builder.create();

        // id uzytkownia idzie po to zeby przyslali spowrotem tylko te grupy do ktorych uzytkownik nie nalezy
        GroupListRequest allGroupsRequest = GroupListRequest.builder()
                .userId(user.getId())
                .build();

        String requestString = RequestFlag.GRPLIST.toString() + gson.toJson(allGroupsRequest);

//        String allGroupsResponseString = client.sendRequestRecResponse(requestString);

        // symulacja poprawnego
        String allGroupsResponseString = ResponseFlag.GRPLIST.toString() +
                "{\n" +
                "  \"items\": [\n" +
                "    {\n" +
                "      \"id\": \"4\",\n" +
                "      \"name\": \"MAD\",\n" +
                "      \"leader\": \"Stronkowski\"\n" +
                "    },\n" +
                "    {\n" +
                "      \"id\": \"3\",\n" +
                "      \"name\": \"FO\",\n" +
                "      \"leader\": \"Gradowski\"\n" +
                "    }\n" +
                "  ]\n" +
                "}\n";

        if(allGroupsResponseString.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            ErrorResponse errorResponse = gson.fromJson(allGroupsResponseString.substring(7), ErrorResponse.class);
            showErrorAlert(errorResponse.getMessage());
            return;
        }

        GroupListResponse groupListResponse = gson.fromJson(allGroupsResponseString.substring(7), GroupListResponse.class);

        List<Group> groups = new ArrayList<>();

        groupListResponse.getItems().forEach(element -> {
            Group g = Group.builder()
                    .id(element.getId())
                    .name(element.getName())
                    .leader(element.getLeader())
                    .build();
            groups.add(g);
        });

        listView.getItems().clear();
        listView.getItems().addAll(groups);
    }

    private void showErrorAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.show();
    }

    void setClient(Client client) {
        this.client = client;
    }

    void setUser(User user) {
        this.user = user;
    }
}
