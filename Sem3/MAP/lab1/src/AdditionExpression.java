import java.util.ArrayList;

public class AdditionExpression extends ComplexExpression {
    public AdditionExpression(ComplexNumber[] args) {
        super(Operation.ADDITION, args);
    }

    @Override
   public ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
       return a.add(b);
   }
}
