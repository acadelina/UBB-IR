using System.Net.Http.Headers;
using System.Net.Http.Json;
using Domain;
using Newtonsoft.Json;

namespace ClientREST;

static class Program
{
    static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));

    private static string URL_Base = "http://localhost:8080/festival/spectacole";

  
    public static void Main(string[] args)
    {
        RunAsync().Wait();
    }
    
    static async Task RunAsync()
    {
        client.BaseAddress = new Uri(URL_Base);
        client.DefaultRequestHeaders.Accept.Clear();
        client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
        
        DateTime date = DateTime.Now;
        string formattedDate = date.ToString("yyyy-MM-ddTHH:mm:ss");
        SpectacolDTO spectacol = new SpectacolDTO{artist="artist",Available_seats = 10,data=formattedDate,Sold_seats = 10,location = "locatie"};
        Console.WriteLine("CREATE SHOW");
        Spectacol rezultat=await CreateSpectacolAsync("http://localhost:8080/festival/spectacole", spectacol);
        Console.WriteLine(rezultat+"\n");
        
        long id=rezultat.Id;
        Console.WriteLine("GETTING SHOW WITH ID: "+id);
        SpectacolDTO foundSpec=await GetSpecatcolAsync("http://localhost:8080/festival/spectacole/" + id);
        Console.WriteLine(foundSpec+"\n");
        
        Console.WriteLine("GETTING ALL SHOWS");
        List<SpectacolDTO> allSpec=await GetSpectacolsAsync("http://localhost:8080/festival/spectacole");
        foreach (var item in allSpec)
        {
            Console.WriteLine(item);
        }
        
        Console.WriteLine("UPDATING SHOW WITH ID: "+id);
        SpectacolDTO spectacolUp = new SpectacolDTO{artist="updated",Available_seats = 15,data=formattedDate,Sold_seats = 10,location = "updated",id=id};
        Spectacol updatdedSpec=await UpdateSpectacolAsync("http://localhost:8080/festival/spectacole/" + id, spectacolUp);
        Console.WriteLine(updatdedSpec+"\n");
        
        Console.WriteLine("DELETING SHOW WITH ID: "+id);
        await DeleteSpectacolAsync("http://localhost:8080/festival/spectacole/" + id);

        
    }
		
    static async Task<SpectacolDTO> GetSpecatcolAsync(string path)
    {
        SpectacolDTO spectacolDto= null;
        HttpResponseMessage response = await client.GetAsync(path);
        if (response.IsSuccessStatusCode)
        {
           spectacolDto = await response.Content.ReadFromJsonAsync<SpectacolDTO>();
        }
        return spectacolDto;
    }
    static async Task<Spectacol> CreateSpectacolAsync(string path, SpectacolDTO spectacolDto)
    {
        Spectacol result = null;
        HttpResponseMessage response = await client.PostAsJsonAsync(path, spectacolDto);
        if (response.IsSuccessStatusCode)
        {
            var spectacolDto2 = await response.Content.ReadFromJsonAsync<SpectacolDTO>();
            result =  new Spectacol(spectacolDto2.artist,DateTime.Parse( spectacolDto2.data), spectacolDto2.location,
                spectacolDto2.Available_seats,spectacolDto2.Sold_seats);
            result.Id=spectacolDto2.id;
        }
        return result;
    }

    static async Task<List<SpectacolDTO>> GetSpectacolsAsync(string path)
    {
        List<SpectacolDTO> result = null;
        HttpResponseMessage response = await client.GetAsync(path);
        if (response.IsSuccessStatusCode)
        {
            result = await response.Content.ReadFromJsonAsync<List<SpectacolDTO>>();
        }
        return result;
    }

    static async Task DeleteSpectacolAsync(string path)
    {
        HttpResponseMessage response = await client.DeleteAsync(path);
        if (response.IsSuccessStatusCode)
        {
            Console.WriteLine("Deleted Spectacol");
        }
        else
        {
            Console.WriteLine("Error deleting Spectacol"+response.StatusCode);
        }
    }

    static async Task<Spectacol> UpdateSpectacolAsync(string path, SpectacolDTO spectacolDto)
    {
        Spectacol result = null;
        HttpResponseMessage response = await client.PutAsJsonAsync(path, spectacolDto);
        if (response.IsSuccessStatusCode)
        {
            SpectacolDTO spectacolDto2 = await response.Content.ReadFromJsonAsync<SpectacolDTO>();
            result = new Spectacol(spectacolDto2.artist,DateTime.Parse( spectacolDto2.data), spectacolDto2.location,
                spectacolDto2.Available_seats, spectacolDto2.Sold_seats);
            result.Id=spectacolDto2.id;
        }
        return result;
        
    }
}

public class SpectacolDTO
{
    [JsonProperty("id")]
    public long id { get; set; }
    [JsonProperty("artist")]
    public string artist { get; set; }
    [JsonProperty("data")]
    public string data { get; set; }
    [JsonProperty("location")]
    public string location { get; set; }
    [JsonProperty("Available_seats")]
    public int Available_seats { get; set; }
    [JsonProperty("Sold_seats")]
    public int Sold_seats { get; set; }

    public override string ToString()
    {
        return string.Format("[Spectacol: Id={0}, artist={1}, data={2}, location={3}, soseats={4}, avseats={5}]", id, artist, data,location, Sold_seats, Available_seats);
    }
}
public class LoggingHandler : DelegatingHandler
{
    public LoggingHandler(HttpMessageHandler innerHandler)
        : base(innerHandler)
    {
    }
    
    protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
    {
        Console.WriteLine("Request:");
        Console.WriteLine(request.ToString());
        if (request.Content != null)
        {
            Console.WriteLine(await request.Content.ReadAsStringAsync());
        }
        Console.WriteLine();
    
        HttpResponseMessage response = await base.SendAsync(request, cancellationToken);
    
        Console.WriteLine("Response:");
        Console.WriteLine(response.ToString());
        if (response.Content != null)
        {
            Console.WriteLine(await response.Content.ReadAsStringAsync());
        }
        Console.WriteLine();
    
        return response;
    }
        
        
}