import java.util.ArrayList;

public class DivisionExpression extends ComplexExpression{
    public DivisionExpression(ComplexNumber[] args) {
        super(Operation.DIVISION, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
        return a.divide(b);
    }
}
