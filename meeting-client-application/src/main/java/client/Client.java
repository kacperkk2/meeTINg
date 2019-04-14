package client;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class Client {

    private Socket clientSocket;
    private OutputStream writer;
    private DataInputStream reader;

    public Client() {
        try {
            clientSocket = new Socket("localhost", 9543);
            writer = clientSocket.getOutputStream();
            reader = new DataInputStream(new BufferedInputStream(clientSocket.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendMessage() {
        char[] message = "WEZ MNIE DAJ GRUPY WSZYSTKIE".toCharArray();
        byte header[] = convertIntToHeader(message.length);

        StringBuilder sb = new StringBuilder();
        sb.append(new String(header));
        sb.append(message);

        String result = sb.toString();
        System.out.println("Cala wiadomosc z naglowkiem: " + result);
        System.out.println("Dlugosc wiadomosci (z naglowkiem): " + result.getBytes().length);

        try {
            writer.write(result.getBytes());

            byte[] response = new byte[128];
            reader.read(response);

            // wyjmuje z naglowka i patrze jaki rozmiar ma wiadomosc
            int mSize = convertHeaderToInt(Arrays.copyOfRange(response, 0, 4));
            System.out.println("Odebrana wiadomosc ma (bez naglowka): " + mSize);

            // wypisuje wiadomosc, bez naglowka
            for(int i = 4; i < mSize+4; i ++)
                System.out.print((char)response[i]);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int convertHeaderToInt(byte[] header) {

        ByteBuffer buffer = ByteBuffer.wrap(header);
        buffer.order(ByteOrder.nativeOrder());
        return buffer.getInt();
    }

    public byte[] convertIntToHeader(int mSize) {

        ByteBuffer buffer = ByteBuffer.allocate(4);
        buffer.order(ByteOrder.nativeOrder());
        buffer.putInt(mSize);
        return buffer.array();
    }

    // metoda ktora konwertuje inta na char[4] na piechote po bitach, moze sie przydac kiedys
//    public char[] convertIntToHeader2(int mSize) {
//
//        int[] bits = new int[32];
//        for (int i = 0; i < 32; i++) {
//            boolean v = (mSize & (1 << i)) != 0;
//            bits[31 - i] = v ? 1 : 0; // 31-i zeby w [0] bylo pierwsze 8 bitow od lewej itd...
//        }
//
//        char[] header = new char[4];
//        for (int i = 0; i < 4; ++i) {
//            int c = 0;
//            for (int j = i * 8; j < (i + 1) * 8; ++j) {
//                c = c << 1;
//                c += bits[j];
//            }
//            header[3-i] = (char)c; // 3-i zeby w [0] bylo pierwsze 8 bitow od lewej itd...
//        }
//
////        System.out.println(Integer.toBinaryString(header[0]));
////        System.out.println(Integer.toBinaryString(header[1]));
////        System.out.println(Integer.toBinaryString(header[2]));
////        System.out.println(Integer.toBinaryString(header[3]));
//        return header;
//    }
}
