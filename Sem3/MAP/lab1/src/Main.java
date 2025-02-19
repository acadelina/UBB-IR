//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
       // System.out.println(args[0]+args[2]);
        ComplexExpression expression= ExpressionParser.parse(args);
        ComplexNumber result= expression.execute();
        System.out.println(result.toString());
    }
}