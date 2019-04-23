package meeting.controller;

import meeting.StageLoader;
import meeting.api.request.UserDataRequest;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import meeting.enums.RequestFlag;
import meeting.enums.ResponseFlag;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.nio.charset.StandardCharsets;

import static com.google.common.hash.Hashing.sha256;

public class RegistrationWindowController {

    @FXML private PasswordField password;
    @FXML private PasswordField confirmPassword;
    @FXML private TextField username;
    @FXML private Button registerButton;
    @FXML private Label infoLabel;

    @FXML
    public void registerClicked(ActionEvent event) {
        if(password.getText().trim().equals(confirmPassword.getText().trim())) {

            // hashuje hasło
            String hashedPassword = sha256()
                    .hashString(password.getText(), StandardCharsets.UTF_8)
                    .toString();

            // tworze requesta
            UserDataRequest request = UserDataRequest.builder()
                    .username(username.getText())
                    .password(hashedPassword)
                    .build();

            // robie JSONa
            GsonBuilder builder = new GsonBuilder();
            builder.setPrettyPrinting();
            Gson gson = builder.create();
            String requestString = RequestFlag.REGISTR.toString() + gson.toJson(request);

            // wysyłam tego requesta, po czym przychodzi response:
//            String responseString = meeting.client.sendRequestRecResponse(requestString);

            // symulacja poprawnego responsa:
            String responseString = ResponseFlag.REGISTR.toString();

            // jesli odpowiedz ze blad, to komunikat i od nowa
            if(responseString.substring(0, 7).equals(ResponseFlag.__ERROR.toString())) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error Dialog");
                // TODO w tego stringa wpakowac komunikat o bledzie z jsona jak przyjdzie error
                String errorMessage = "Username occupied :(";
                alert.setHeaderText(errorMessage);
                alert.showAndWait();
            }
            // jesli odpowiedz ze zapisano uzytkownika to komunikat i do okna logowania
            else if(responseString.substring(0, 7).equals(ResponseFlag.REGISTR.toString())) {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Information Dialog");
                alert.setHeaderText("Account created :)");
                alert.showAndWait();

                cancelClicked(event);
            }
        }
        else {
            infoLabel.setText("Passwords doesnt match");
        }
    }

    @FXML
    public void cancelClicked(ActionEvent event) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/fxml/LoginWindow.fxml"));
            StageLoader.loadStage((Stage)((Node) event.getSource()).getScene().getWindow(), fxmlLoader);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void fieldChanged() {
        registerButton.setDisable(username.getText().trim().isEmpty() ||
                password.getText().trim().isEmpty() || confirmPassword.getText().trim().isEmpty());

        if(!infoLabel.getText().isEmpty())
            infoLabel.setText("");
    }
}
