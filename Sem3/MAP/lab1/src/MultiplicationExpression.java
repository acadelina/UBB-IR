import java.util.ArrayList;

public class MultiplicationExpression extends ComplexExpression{

    public MultiplicationExpression( ComplexNumber[] args) {
        super(Operation.MULTIPLICATION, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
        return a.multiply(b);
    }
}
