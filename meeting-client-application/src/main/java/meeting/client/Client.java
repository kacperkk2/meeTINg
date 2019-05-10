package meeting.client;

import java.io.*;

import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Client {

    private OutputStream writer;
    private DataInputStream reader;

    private byte[] bufferPackage; // zbiera paczke tutaj
    private byte[] portion; // pojedyncze porcje od read socket
    private int bytesNeeded; // ile bajtow potrzebujemy jeszcze
    private int bytesReceived; // ile juz otrzymalismy
    private int messageSize; // jak juz wiemy ile ma wiadomosc, inaczej -1
    private int packageSize; // jak juz wiemy ile ma paczka, inaczej -1
    private int bytesFromRead; // ile bajtow pobrac read socket

    public Client() {
        try {
            Socket clientSocket = new Socket("localhost", 9543);
            writer = clientSocket.getOutputStream();
            reader = new DataInputStream(new BufferedInputStream(clientSocket.getInputStream()));

            init();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void init() {
        bytesNeeded = 128; // ile chcemy za pierwszym zamahem pobrac bajtow
        bufferPackage = new byte[bytesNeeded]; // robie bufor zeby pomiescil ten pierwszy rzut
        messageSize = -1;
        bytesReceived = 0;
        packageSize = -1;
        bytesFromRead = 0;
    }

    public String sendRequestRecResponse(String request) {

        // przychodzi sam json w stringu, wiec dodajemy do niego dlugosc i to jest paczka
        String requestPackage = addHeader(request);

        System.out.println("Do wyslania wiadomosc (z header): " + requestPackage);
        System.out.println("Do wyslania bajtow (z naglowkiem): " + requestPackage.getBytes().length);

        // wysyla naszego requesta
        sendRequest(requestPackage.getBytes());

        // odbierze cala pacze i umiesci w bufferPackage
        receiveResponse();
        String response = removeHeader(bufferPackage);

        System.out.println("Odebrana wiadomosc (bez header): " + response);
        System.out.println("Odebrana bajtow (bez header): " + messageSize);

        // mam juz odpowiedz dla wyzszej warstwy wiec szykuje na nastepny odbior
        init();

        return response;
    }

    private String removeHeader(byte[] responsePackage) {

        // biore pierwsze 4 bajty paczki, na nich jest zapisany rozmiar dalszej czesci
        //int mSize = convertHeaderToInt(Arrays.copyOfRange(responsePackage, 0, 4));

        // wycinam naglowek
        byte[] response = Arrays.copyOfRange(responsePackage, 4, packageSize);

        String responseString;
        responseString = new String(response, StandardCharsets.UTF_8);

        return responseString;
    }

    private void receiveResponse() {

        while(bytesReceived != packageSize) {
            portion = new byte[bytesNeeded];

            try {
                bytesFromRead = reader.read(portion);

            } catch (IOException e) {
                e.printStackTrace();
            }

            handlePortion();
        }
    }

    private void handlePortion() {
        System.arraycopy(portion, 0, bufferPackage, bytesReceived, bytesFromRead);
        bytesReceived += bytesFromRead;
        bytesNeeded -= bytesFromRead;

        System.out.println("bytesreceived: " + bytesReceived);

        // jesli mamy juz naglowek a jeszcze nie wyliczylismy rozmiaru, to go wyliczmy
        if(bytesReceived >= 4 && messageSize == -1)
        {
            messageSize = convertHeaderToInt(Arrays.copyOfRange(bufferPackage, 0, 4));
            packageSize = messageSize + 4;

            // naglowek juz mam wiec potrzebuje jeszcze tyle ile ma cala paczka minus to co juz odebralem
            bytesNeeded = packageSize - bytesReceived;

            // jak juz wiem ile bajtow ma cala paczka, to alokuje bufor i przerzucam tam dotychczasowe dane
            byte[] tmp = Arrays.copyOfRange(bufferPackage, 0, bytesReceived);
            //System.arraycopy(bufferPackage, 0, tmp, 0, bytesReceived);
            bufferPackage = new byte[packageSize];

            System.out.println("packageSize: " + packageSize);

            //tu sie wywala client
            System.arraycopy(tmp, 0, bufferPackage, 0, bytesReceived);

        }
    }

    private void sendRequest(byte[] requestPackage) {
        try {
            // chyba java martwi sie o to zeby to zostalo cale wyslane
            writer.write(requestPackage);

            writer.flush(); // czy z tym???
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String addHeader(String message) {
        // dlugosc wiadomosci do tablicy header[4]
        byte[] header = convertIntToHeader(message.length());

        // cala paczka to header + wiadomosc
        return new String(header) + message;
    }

    private int convertHeaderToInt(byte[] header) {

        ByteBuffer buffer = ByteBuffer.wrap(header);
        buffer.order(ByteOrder.nativeOrder());
        return buffer.getInt();
    }

    private byte[] convertIntToHeader(int mSize) {

        ByteBuffer buffer = ByteBuffer.allocate(4);
        buffer.order(ByteOrder.nativeOrder());
        buffer.putInt(mSize);
        return buffer.array();
    }
}
