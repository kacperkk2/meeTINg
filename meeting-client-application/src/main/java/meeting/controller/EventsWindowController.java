package meeting.controller;

import javafx.scene.control.*;
import meeting.StageLoader;
import meeting.api.request.EventListRequest;
import meeting.api.request.NewEventRequest;
import meeting.api.response.ErrorResponse;
import meeting.api.response.EventListResponse;
import meeting.api.response.NewEventResponse;
import meeting.client.Client;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import meeting.enums.RequestFlag;
import meeting.enums.ResponseFlag;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import meeting.model.Event;
import meeting.model.Group;
import meeting.model.User;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static meeting.enums.SystemRole.USER;


public class EventsWindowController {

    @FXML public Button createButton;
    @FXML public Button refreshButton;
    @FXML public Button returnButton;
    @FXML public Button signOutButton;
    @FXML public ListView<Event> eventList;

    private Group pickedGroup;
    private Client client;
    private User user;

    @FXML
    public void initialize() {
        Platform.runLater(() ->{
            if(user.getSystemRole() == USER) {
                createButton.setDisable(true);
            }
            refreshClicked();
        });
    }

    @FXML
    public void signOutClicked(ActionEvent actionEvent) {
        // TODO wyslanie requesta o wylogowanie, ale czy potrzeba???
        // Tomek: potrzeba chyba przynajmniej dlatego zeby serwer mogl wywalic sockety zwiazane z tym uzytkownikiem

        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setHeaderText(null);
        alert.setContentText("Do you want to sign out?");

        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent()) {
            ButtonType reloadedResult = result.get();
            if (reloadedResult == ButtonType.OK){
                try {
                    FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/LoginWindow.fxml"));
                    StageLoader.loadStage((Stage)((Node) actionEvent.getSource()).getScene().getWindow(), fxmlLoader);
                } catch(Exception e) {
                    e.printStackTrace();
                }
            }
        }

    }

    @FXML
    public void returnClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/GroupsWindow.fxml"));
            StageLoader.loadStage((Stage)((Node) actionEvent.getSource()).getScene().getWindow(), fxmlLoader);
            GroupsWindowController groupsWindowController = fxmlLoader.getController();
            groupsWindowController.setClient(client);
            groupsWindowController.setUser(user);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void refreshClicked() {
        // robie JSONa
        GsonBuilder builder = new GsonBuilder();
        builder.setPrettyPrinting();
        Gson gson = builder.create();

        EventListRequest request = EventListRequest.builder()
                .groupId(pickedGroup.getId())
                .build();

        String requestString = RequestFlag.GRPEVNT.toString() + gson.toJson(request);

//        String response = meeting.client.sendRequestRecResponse(request);

        String response = ResponseFlag.GRPEVNT.toString() +
                "{\n" +
                "  \"items\": [\n" +
                "    {\n" +
                "      \"id\": \"101\",\n" +
                "      \"name\": \"Idziemy na piwko\"\n" +
                "    },\n" +
                "    {\n" +
                "      \"id\": \"102\",\n" +
                "      \"name\": \"Jedziemy na działkę\"\n" +
                "    },\n" +
                "    {\n" +
                "      \"id\": \"103\",\n" +
                "      \"name\": \"Jedziemy do Jozefa Polovki\"\n" +
                "    }\n" +
                "  ]\n" +
                "}\n";

        if(response.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            // TODO obsługa błędu pobrania listy eventów
            return;
        }

        EventListResponse eventListResponse = gson.fromJson(response.substring(7), EventListResponse.class);

        List<Event> events = new ArrayList<>();

        eventListResponse.getItems().forEach(element -> {
            Event e = Event.builder()
                    .id(element.getId())
                    .name(element.getName())
                    .build();
            events.add(e);
        });

        eventList.getItems().clear();
        eventList.getItems().addAll(events);
    }

    @FXML
    public void createClicked() {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("New event");
        dialog.setHeaderText(null);
        dialog.setContentText("Please enter event name:");

        Optional<String> result = dialog.showAndWait();

        result.ifPresent(name -> {
            if (name.equals("")) showNewEventErrorAlert("Field can not be empty!");
            else {
                sendNewEventRequest(name);
            }
        });
    }

    private void sendNewEventRequest(String name) {
        // robie JSONa
        GsonBuilder builder = new GsonBuilder();
        builder.setPrettyPrinting();
        Gson gson = builder.create();

        NewEventRequest newEventRequest = NewEventRequest.builder()
                .groupId(pickedGroup.getId())
                .eventName(name)
                .build();

        String request = RequestFlag.MAKEEVT.toString() + gson.toJson(newEventRequest);

//        String response = meeting.client.sendRequestRecResponse(request);

        String response = ResponseFlag.MAKEEVT.toString() +
                "{\n" +
                "  \"id\": \"65\",\n" +
                "  \"name\": \"Nowy event\"\n" +
                "}\n";

        if(response.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            ErrorResponse errorResponse = gson.fromJson(response.substring(7), ErrorResponse.class);
            showNewEventErrorAlert(errorResponse.getMessage());
            return;
        }

        NewEventResponse newEventResponse = gson.fromJson(response.substring(7), NewEventResponse.class);

        Event e = Event.builder()
                .id(newEventResponse.getId())
                .name(newEventResponse.getName())
                .build();

        eventList.getItems().add(e);
    }

    private void showNewEventErrorAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.show();
    }

    @FXML
    public void eventClicked(MouseEvent mouseEvent) {
        System.out.println("eventClicked");
    }

    void setPickedGroup(Group pickedGroup) {
        this.pickedGroup = pickedGroup;
    }

    void setClient(Client client) {
        this.client = client;
    }

    void setUser(User user) {
        this.user = user;
    }
}
