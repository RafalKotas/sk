package pl.put.client;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 * Created by Hubert on 17.10.2018.
 */
public class Main {

    public static void main(String... args) {
        try(Socket socket = new Socket(args[0], Integer.valueOf(args[1]))) {
            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());
            outputStream.writeUTF(args[2]);
            outputStream.flush();
            String s = inputStream.readUTF();
            System.out.println(s);

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}