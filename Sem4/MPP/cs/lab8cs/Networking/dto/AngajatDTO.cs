using System.Text.Json.Serialization;

namespace Networking.dto;
using Domain;
public class AngajatDTO:EntityDTO
{
    [JsonInclude]
    public string Username{ get; set; }
    [JsonInclude]
    public string Password{ get; set; }
    [JsonInclude]
    public string Mail{ get; set; }

    [JsonConstructor]
    public AngajatDTO(string username, string password, string mail)
    {
        this.Username = username;
        this.Password = password;
        this.Mail = mail;
    }
    

    public static AngajatDTO fromAngajat(Angajat angajat)
    {
        var a=new AngajatDTO(angajat.Username,angajat.Password,angajat.Mail);
        a.Id = angajat.Id;
        return a;
    }

    public Angajat toAngajat()
    {
        var a=new Angajat(Username, Password, Mail);
        a.Id = Id;
        return a;
    }
    
}