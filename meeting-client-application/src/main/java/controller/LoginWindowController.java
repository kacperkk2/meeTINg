package controller;

import api.request.GroupListRequest;
import api.request.UserLoginRequest;
import api.response.GroupListResponse;
import api.response.UserLoginResponse;
import client.Client;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import enums.RequestFlag;
import enums.ResponseFlag;
import enums.SystemRole;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import model.Group;
import model.User;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

import static com.google.common.hash.Hashing.sha256;

public class LoginWindowController {

    private Client client;

    private User user;

    @FXML private TextField usernameField;
    @FXML private PasswordField passwordField;

    @FXML
    public void signInClicked(ActionEvent event) {

        // hashuje hasło
        String hashedPassword = sha256()
                .hashString(passwordField.getText(), StandardCharsets.UTF_8)
                .toString();

        // tworze requesta
        UserLoginRequest request = UserLoginRequest.builder()
                .username(usernameField.getText())
                .password(hashedPassword)
                .build();

        // robie JSONa
        GsonBuilder builder = new GsonBuilder();
        builder.setPrettyPrinting();
        Gson gson = builder.create();
        String requestString = RequestFlag.LOGGING.toString() + gson.toJson(request);

        // wysyłam tego requesta, po czym przychodzi response:
//        String responseString = client.sendRequestRecResponse(requestString);

        //symulacja poprawnego responsa:
        String responseString = ResponseFlag.LOGGING.toString() +
                "{\n" +
                "  \"id\": \"1\",\n" +
                "  \"username\": \"asd123_#\",\n" +
                "  \"password\": \"b790d976a02850ac9d5605e92ac7283ac477c76c203556fdd94726dd106cdae3\",\n" +
                "  \"systemRole\": USER\n" +
                "}";

        if (responseString.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            // TODO obsługa niepoprawnego logowania. Teraz wchodzi w tego ifa po wywołaniu sendRequestRecResponse, bo to zwraca flage LOGGING
            return;
        }

        // parsuje JSONa
        UserLoginResponse response = gson.fromJson(responseString.substring(7), UserLoginResponse.class);

        // tworze obiekt użytkownika
        user = User.builder()
                .id(response.getId())
                .username(response.getUsername())
                .password(response.getPassword())
                .systemRole(SystemRole.valueOf(response.getSystemRole()))
                .build();

        GroupListRequest groupRequest = GroupListRequest.builder()
                .userId(user.getId())
                .build();

        requestString = RequestFlag.USERGRP.toString() + gson.toJson(groupRequest);

//        String groupResponseString = client.sendRequestRecResponse(requestString);

        String groupResponseString = ResponseFlag.USERGRP.toString() +
                "{\n" +
                "  \"items\": [\n" +
                "    {\n" +
                "      \"id\": \"1\",\n" +
                "      \"name\": \"TKOM\",\n" +
                "      \"leader\": \"Gawkowski\"\n" +
                "    },\n" +
                "    {\n" +
                "      \"id\": \"21\",\n" +
                "      \"name\": \"TIN\",\n" +
                "      \"leader\": \"Blinowski\"\n" +
                "    }\n" +
                "  ]\n" +
                "}\n";

        if(groupResponseString.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
            // TODO obsługa błędu pobrania listy grup
            return;
        }

        GroupListResponse groupListResponse = gson.fromJson(groupResponseString.substring(7), GroupListResponse.class);

        List<Group> groups = new ArrayList<>();

        groupListResponse.getItems().forEach(element -> {
            Group g = Group.builder()
                    .id(element.getId())
                    .name(element.getName())
                    .leader(element.getLeader())
                    .build();
            groups.add(g);
        });

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
