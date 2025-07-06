namespace Networking.rpcprotocol;

[Serializable]
public class Request
{
    private Request() { }
        
    public RequestType Type { get; private set; }
    public object Data { get; private set; }
    

    public override string ToString()
    {
        return $"Request{{type='{Type}', data='{Data}'}}";
    }

    public class Builder
    {
        private Request request = new Request();

        public Builder Type(RequestType type)
        {
            request.Type = type;
            return this;
        }

        public Builder Data(object data)
        {
            request.Data = data;
            return this;
        }

        public Request Build()
        {
            return request;
        }
    }

}