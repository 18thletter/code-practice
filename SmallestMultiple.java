import java.io.*;
import java.util.*;

class SmallestMultiple {
    public static Set<Integer> primes = new HashSet<Integer>();
    public static List<Integer> primeFactors = new ArrayList<Integer>();

    public static void main (String[] args) {
        int bottomRange = Integer.parseInt(args[0]);
        int topRange = Integer.parseInt(args[1]);
        // find all prime factors of numbers in the range
        // and multiply them together
        for (int i = bottomRange; i <= topRange; ++i) {
            // find the prime factors of i
            if (isPrime(i)) {
                primes.add(i);
                primeFactors.add(i);
                continue;
            }
            // if not a prime, divide i into prime factors
            int n = i;
            List<Integer> tempFactors = new ArrayList<Integer>(primeFactors);
            List<Integer> addToPrimeFactors = new ArrayList<Integer>();
            for (Integer p : primes) {
                while (n % p == 0) {
                    n /= p;
                    if (!tempFactors.remove(p)) {
                        addToPrimeFactors.add(p);
                    }
                }
            }
            primeFactors.addAll(addToPrimeFactors);
        }
        int smallestMultiple = 1;
        for (Integer n : primeFactors) {
            smallestMultiple *= n;
        }
        System.out.println(smallestMultiple);
    }

    // excluding 1 as a prime for ease
    public static boolean isPrime(int n) {
        for (Integer p : primes) {
            if (n % p == 0) {
                return false;
            }
        }
        return n == 1 ? false : true;
    }
}
