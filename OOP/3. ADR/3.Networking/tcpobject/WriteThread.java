import java.io.IOException;
import java.util.Scanner;

public class WriteThread implements Runnable {

    private final Thread thr;
    private final SocketWrapper socketWrapper;
    final String name;

    public WriteThread(SocketWrapper socketWrapper, String name) {
        this.socketWrapper = socketWrapper;
        this.name = name;
        this.thr = new Thread(this);
        thr.start();
    }

    @Override
    public void run() {
        try (Scanner input = new Scanner(System.in)) {
            int i = 1;
            while (true) {
                System.out.println("Enter a message to send: ");
                String s = input.nextLine();
                Data d = new Data();
                d.setId(i);
                d.setValue(s);
                socketWrapper.write(d);
                i++;
            }
        } catch (IOException e) {
            System.out.println("WriteThread error: " + e.getMessage());
        } finally {
            try {
                socketWrapper.closeConnection();
            } catch (IOException e) {
                System.out.println("Error closing connection: " + e.getMessage());
            }
        }
    }
}
