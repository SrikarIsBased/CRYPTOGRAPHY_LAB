import java.util.Scanner;

public class Arithmetic
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("===== ARITHMETIC OPERATIONS IN JAVA =====");
        System.out.print("Enter number of test cases: ");
        int t = sc.nextInt();

        for (int i = 1; i <= t; i++)
        {
            System.out.println("\nTest Case " + i);
            System.out.print("Enter first number a: ");
            long a = sc.nextLong();
            System.out.print("Enter second number b: ");
            long b = sc.nextLong();

            System.out.println("Addition       : " + a + " + " + b + " = " + (a + b));
            System.out.println("Subtraction    : " + a + " - " + b + " = " + (a - b));
            System.out.println("Multiplication : " + a + " * " + b + " = " + (a * b));
            if (b == 0)
            {
                System.out.println("Division       : Not possible (division by zero)");
                System.out.println("Modulus        : Not possible (division by zero)");
            }
            else
            {
                System.out.printf("Division       : %d / %d = %.4f%n", a, b, (double) a / b);
                System.out.println("Modulus        : " + a + " % " + b + " = " + (a % b));
            }
        }

        sc.close();
    }
}
