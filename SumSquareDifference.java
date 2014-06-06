import java.io.*;

class SumSquareDifference {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        long sumOfSquares = n * (n + 1) * (2 * n + 1) / 6;
        long squareOfSums = (long) Math.pow(n * (n + 1) / 2, 2);
        System.out.println(Math.abs(squareOfSums - sumOfSquares));
    }
}
