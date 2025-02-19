public class ComplexNumber {
    private double real,imaginary;
    public ComplexNumber() {
        this.real = 0;
        this.imaginary = 0;
    }
    public ComplexNumber(String number) {
        real=0;
        imaginary=0;

        if(number.charAt(number.length()-1)!='i'){
            //when it does not have an imaginary part
            real = Double.parseDouble(number);
        }
        else
        {
            //when it has an imaginary part
            boolean isNegative=false;
            String[] parts = number.split("[-+]");

            if(parts[0].equals(""))
            {
                //when the number is negative
                isNegative=true;
            }
            if(parts.length==1)
            {
                //case bi


                if(parts[0].length()==1)
                {
                    if(number.charAt(number.length()-1)!='-')
                        imaginary=-1;
                    else
                        imaginary=1;
                }
                else {
                    parts[0] = parts[0].substring(0, parts[0].length() - 2);
                    imaginary = Double.parseDouble(parts[0]);
                }
            }
            if(parts.length==2)
            {
                if(isNegative) {
                    //case -bi
                    parts[1] = parts[1].substring(0, number.length() - 2);
                    if (parts[1].equals(""))
                        imaginary = -1;
                    else
                        imaginary = -1 * Double.parseDouble(parts[1]);
                }
                else
                {
                    //case a+bi/ a-bi
                    parts[1] = parts[1].substring(0, parts[1].length() - 2);
                    real = Double.parseDouble(parts[0]);
                    if(parts[1].equals(""))
                        imaginary = 1;
                    else
                        imaginary = Double.parseDouble(parts[1]);
                    if(number.indexOf('-')>=0)
                        imaginary=-imaginary;
                }
            }
            if(parts.length==3)
            {
                //case -a+bi/-a-bi
                if(parts[2].length()!=1)
                    parts[2]=parts[2].substring(0,parts[2].length()-2);
                else
                    parts[2] = parts[2].substring(0, parts[2].length()-1);
                real=(-1)*Double.parseDouble(parts[1]);
                if(parts[2].equals(""))
                    imaginary=1;
                else
                    imaginary=Double.parseDouble(parts[2]);
                number=number.substring(1);
                if(number.indexOf('-')>=0)
                    imaginary=-imaginary;
            }

        }
    }

    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    public ComplexNumber add(ComplexNumber addend) {
        this.setReal(this.getReal()+addend.getReal());
        this.setImaginary(this.getImaginary()+addend.getImaginary());
        return this;
    }

    public ComplexNumber subtract(ComplexNumber subtrahend) {
        this.setReal(this.getReal()-subtrahend.getReal());
        this.setImaginary(this.getImaginary()-subtrahend.getImaginary());
        return this;
    }

    public ComplexNumber multiply(ComplexNumber multiplicand) {
        double result=this.real*multiplicand.getReal()+this.imaginary*multiplicand.getImaginary();
        this.setImaginary(this.real*multiplicand.getImaginary()+this.imaginary*multiplicand.getReal());
        this.setReal(result);
        return this;
    }

    public ComplexNumber divide(ComplexNumber divisor) {
        double result=(this.real*divisor.getReal()+this.imaginary*divisor.getImaginary())/(divisor.getReal()* divisor.getReal()+ divisor.getImaginary()*divisor.getImaginary());
        this.setImaginary((divisor.getReal()*this.imaginary-this.real*divisor.getImaginary())/(divisor.getReal()* divisor.getReal()+divisor.getImaginary()* divisor.getImaginary()));
        this.setReal(result);
        return this;
    }

    @Override
    public String toString() {
        boolean hasReal=(real!=0);
        boolean hasImaginary=(imaginary!=0);
        if(!hasReal && !hasImaginary)
            return "0";
        String realResult="";
        if(hasReal)
        {

            realResult+=String.valueOf(real);
        }
        String sign=(hasReal && (imaginary>0) ? "+" : "");
        String imaginaryResult=sign+imaginary+"*i";
        if(imaginary==1)
            imaginaryResult=sign+"*i";
        if(imaginary==-1)
            imaginaryResult="*-i";
        return realResult+(hasImaginary ? imaginaryResult : "");
    }
}
