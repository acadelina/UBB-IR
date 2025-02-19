package ubb.scs.map.socialNetwork.domain.validators;

import ubb.scs.map.socialNetwork.domain.FriendRequest;

public class FriendRequestValidator implements Validator<FriendRequest> {
    @Override
    public void validate(FriendRequest friendRequest) {
        Long id1 = friendRequest.getId().getE1();
        Long id2 = friendRequest.getId().getE2();

        if(id1.equals(id2))
            throw new ValidationException("Id-ul nu poate sa fie acelasi!");
    }
}
