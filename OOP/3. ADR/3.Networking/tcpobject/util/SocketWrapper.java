import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class SocketWrapper {

    private final Socket socket;
    private final ObjectOutputStream oos;
    private final ObjectInputStream ois;

    public SocketWrapper(String address, int port) throws IOException {
        this.socket = new Socket(address, port);
        oos = new ObjectOutputStream(socket.getOutputStream());
        ois = new ObjectInputStream(socket.getInputStream());
    }

    public SocketWrapper(Socket socket) throws IOException {
        this.socket = socket;
        oos = new ObjectOutputStream(socket.getOutputStream());
        ois = new ObjectInputStream(socket.getInputStream());
    }

    public Object read() throws IOException, ClassNotFoundException {
        return ois.readObject();
    }

    public void write(Object o) throws IOException {
        oos.writeObject(o);
        oos.flush();
    }

    public void closeConnection() throws IOException {
        ois.close();
        oos.close();
        socket.close();
    }
}
