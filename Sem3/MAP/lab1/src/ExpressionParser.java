public class ExpressionParser {
    public static ComplexExpression parse(String[] expression) {
        ComplexNumber[] numbers = new ComplexNumber[expression.length/2+1];
        Operation operation=null;

        int index=0;
        for(int i=0;i<expression.length;i++) {
            if(i%2==0)
            {
                numbers[index++]=new ComplexNumber(expression[i]);
            }
            else
            {

                switch(expression[i]){
                    case "+":
                        operation=Operation.ADDITION;
                        break;
                    case "-":
                        operation=Operation.SUBSTRACTION;
                        break;
                    case "*":
                        operation=Operation.MULTIPLICATION;
                        break;
                    case "/":
                        operation=Operation.DIVISION;
                        break;
                    default:
                        throw new ArithmeticException("Invalid expression");
                }
            }
        }
        return ExpressionFactory.getInstance().createComplexExpression(operation,numbers);
    }
}
