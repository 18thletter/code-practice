import java.io.*;

class LargestPrimeFactor {
    public static void main (String[] args) {
        long target = Long.valueOf(args[0]).longValue();
        long largestDivisor = 1;
        if (target % 2 == 0) {
            largestDivisor = 2;
            while (target % 2 == 0) {
                target /= 2;
            }
        }
        long divisor = 3;
        while (target > 1) {
            if (target % divisor == 0) {
                largestDivisor = divisor;
                while (target % divisor == 0) {
                    target /= divisor;
                }
            }
            divisor += 2;
        }

        System.out.println(largestDivisor);
    }
}
