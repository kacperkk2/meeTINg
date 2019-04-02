import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Screen;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Main extends Application {


    public static void main(String[] args) {
        launch(args);

//        try {
//            String sentence;
//            String modifiedSentence;
//            BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
//            Socket clientSocket = new Socket("localhost", 9543);
//            DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
//            BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
//            sentence = inFromUser.readLine();
//            outToServer.writeBytes(sentence);
//            modifiedSentence = inFromServer.readLine();
//            System.out.println("FROM SERVER: " + modifiedSentence);
//            clientSocket.close();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }

    @Override
    public void start(Stage primaryStage) {
        Rectangle2D primScreenBounds = Screen.getPrimary().getVisualBounds();
        Stage loginStage = new Stage();

        loadStage(loginStage, "/fxml/LoginWindow.fxml", "meeTINg Client Application");
        loginStage.show();
        loginStage.setWidth(640);
        loginStage.setHeight(480);
        loginStage.setX((primScreenBounds.getWidth()/2) - 320);
        loginStage.setY((primScreenBounds.getHeight()/2) - 240);
    }

    private void loadStage(Stage stage, String resourcePath, String title)
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource(resourcePath));
            AnchorPane root = fxmlLoader.load();
            root.setId("userLogin");
            Scene scene = new Scene(root);
            scene.getStylesheets().addAll(this.getClass().getResource("css/background.css").toExternalForm());
            stage.setScene(scene);
            stage.setTitle(title);
            stage.setResizable(false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
