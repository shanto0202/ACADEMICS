import java.io.IOException;

public class ReadThread implements Runnable {

    private final Thread thr;
    private final SocketWrapper socketWrapper;

    public ReadThread(SocketWrapper socketWrapper) {
        this.socketWrapper = socketWrapper;
        this.thr = new Thread(this);
        thr.start();
    }

    @Override
    public void run() {
        try {
            while (true) {
                Object o = socketWrapper.read();
                if (o instanceof Data) {
                    Data obj = (Data) o;
                    System.out.println("Received: " + obj.getId() + ", " + obj.getValue());
                }
            }
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("ReadThread error: " + e.getMessage());
        } finally {
            try {
                socketWrapper.closeConnection();
            } catch (IOException e) {
                System.out.println("Error closing connection: " + e.getMessage());
            }
        }
    }
}
