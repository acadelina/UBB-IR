public class ExpressionFactory {
    private static ExpressionFactory instance ;
    private ExpressionFactory() {
    }
    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    public ComplexExpression createComplexExpression(Operation operation, ComplexNumber[] args) {
        switch (operation)
        {
            case ADDITION :
               return new AdditionExpression(args);
            case MULTIPLICATION :
               return new MultiplicationExpression(args);
            case DIVISION :
               return new DivisionExpression(args);
            case SUBSTRACTION:
               return new SubstractionExpression(args);
            default:
                throw new IllegalArgumentException("Operation not recognized");
        }
    }
}
