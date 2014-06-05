import java.io.*;
import java.util.*;

class LargestPalindromeProduct {
    public static void main (String[] args) {
        int digits = Integer.parseInt(args[0]);
        // both start at largest number with those digits
        int max = (int) Math.pow(10, digits) - 1;
        int firstMultipleDistance = 0, secondMultipleDistance = 0;
        int bottomLimit = (int) Math.pow(10, digits - 1);
        boolean palindromeFound = false;
        long product = 0;
        // distance is the combined difference the two multiples are from the highest
        // value
        List<Integer> distance = new ArrayList<Integer>();
        distance.add(0);
        while (max - firstMultipleDistance >= bottomLimit && max - secondMultipleDistance >= bottomLimit) {
            int size = distance.size();
            // start in the middle and go outward
            int i, j, runs;
            if (size % 2 == 0) {
                i = size / 2 - 1;
                j = size / 2;
                runs = size / 2;
            } else {
                i = j = size / 2;
                runs = size / 2 + 1;
            }
            for (int c = 0; c < runs; --i, ++j, ++c) {
                firstMultipleDistance = distance.get(i);
                secondMultipleDistance = distance.get(j);
                product = (long) ((max - firstMultipleDistance) * (max - secondMultipleDistance));
                if (isPalindrome(product)) {
                    palindromeFound = true;
                    break;
                }
            }
            if (palindromeFound) {
                break;
            }
            distance.add(distance.get(distance.size() - 1) + 1);
        }
        System.out.println(product);
    }

    public static boolean isPalindrome(long product) {
        String s = String.valueOf(product);
        int len = s.length();
        for (int i = 0; i < len / 2; ++i) {
            if (s.charAt(i) != s.charAt(len - 1 - i)) {
                return false;
            }
        }
        return true;
    }
}
