import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class FastIO {
    final private static int BUFFER_SIZE = 1 << 16;

    private DataInputStream in;
    private DataOutputStream out;
    private byte[] inBuffer;
    private byte[] outBuffer;
    private int inPointer, bytesRead, outPointer;

    public FastIO() {
        in = new DataInputStream(System.in);
        out = new DataOutputStream(System.out);
        inBuffer = new byte[BUFFER_SIZE];
        outBuffer = new byte[BUFFER_SIZE];
        inPointer = bytesRead = outPointer = 0;
    }

    public String nextWord() throws IOException {
        byte c = read();
        while (Character.isWhitespace(c)) {
            c = read();
        }
        StringBuilder builder = new StringBuilder();
        builder.append((char) c);
        c = read();
        while (!Character.isWhitespace(c)) {
            builder.append((char) c);
            c = read();
        }
        return builder.toString();
    }

    public String readLine() throws IOException {
        StringBuilder builder = new StringBuilder();
        byte c;
        while ((c = read()) != -1 && (char) c != '\n') {
            builder.append((char) c);
        }
        return builder.toString();
    }

    public int nextInt() throws IOException {
        int value = 0;
        byte c = read();
        while (Character.isWhitespace(c)) {
            c = read();
        }
        boolean neg = c == '-';
        if (neg) {
            c = read();
        }
        value = c - '0';
        while ((c = read()) >= '0' && c <= '9') {
            value = value * 10 + c - '0';
        }
        if (neg) {
            value = -value;
        }
        return value;
    }

    public void println(String str) throws IOException {
        write(str + "\n");
    }

    public void println(Integer i) throws IOException {
        write(i.toString() + "\n");
    }
    
    private byte read() throws IOException {
        if (inPointer == bytesRead) {
            inPointer = 0;
            bytesRead = in.read(inBuffer, inPointer, BUFFER_SIZE);
        }
        return inBuffer[inPointer++];
    }
    
    public void write(String str) throws IOException {
        writeBytes(str.getBytes());
    }
    
    private void writeBytes(byte arr[]) throws IOException {
        int bytesToWrite = arr.length;
        if (outPointer + bytesToWrite >= BUFFER_SIZE) {
            flush();
        }
        for (int i = 0; i < bytesToWrite; i++, outPointer++) {
            outBuffer[outPointer] = arr[i];
        }
    }

    public void flush() throws IOException {
        out.write(outBuffer, 0, outPointer);
        out.flush();
        outPointer = 0;
    }

    public void close() throws IOException {
        if (in != null) {
            in.close();
        }
        if (out != null) {
            flush();
            out.close();
        }
    }
}