import java.util.ArrayList;

public class SubstractionExpression extends ComplexExpression{
    public SubstractionExpression(ComplexNumber[] args) {
        super(Operation.SUBSTRACTION, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
        return a.subtract(b);
    }
}
