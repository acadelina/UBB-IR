namespace WinFormsApp1.Service;

public class ServiceException:Exception
{
    public ServiceException(string message) : base(message){}
}