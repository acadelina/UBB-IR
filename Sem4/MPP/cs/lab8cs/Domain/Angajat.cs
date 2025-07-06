namespace Domain;

public class Angajat:Entity<long>
{
    public Angajat(string username, string password, string mail)
    {
        Username = username;
        Password = password;
        Mail= mail;
    }
    
    public string Username { get; set; }
    public string Password { get; set; }
    public string Mail { get; set; }

    public override string ToString()
    {
        return Username+":"+Password+":"+Mail;
    }
}