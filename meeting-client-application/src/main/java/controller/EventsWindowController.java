package controller;

import api.request.EventListRequest;
import api.response.EventListResponse;
import client.Client;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import enums.RequestFlag;
import enums.ResponseFlag;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import model.Event;
import model.Group;
import model.User;

import java.util.ArrayList;
import java.util.List;


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
    public void signOutClicked(ActionEvent actionEvent) {
        System.out.println("signOutClicked");
    }

    @FXML
    public void returnClicked(ActionEvent actionEvent) {
        System.out.println("returnClicked");
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

//        String response = client.sendRequestRecResponse(request);

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

    public void setClient(Client client) {
        this.client = client;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
