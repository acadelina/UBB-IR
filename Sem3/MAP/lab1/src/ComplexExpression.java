//import jdk.dynalink.Operation;

import java.util.ArrayList;

public abstract class ComplexExpression {
    Operation operation;
    ComplexNumber[] args;

    public ComplexExpression(Operation operation, ComplexNumber[] args) {
        this.operation = operation;
        this.args = args;
    }

    public abstract ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b);

    public ComplexNumber execute(){
        ComplexNumber result=args[0];
        for(int i=1;i<args.length;i++)
        {
            result=executeOneOperation(result,args[i]);
        }
        return result;
    }
}
