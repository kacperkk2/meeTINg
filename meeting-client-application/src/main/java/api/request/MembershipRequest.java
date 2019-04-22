package api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class MembershipRequest {

    private long userId;
    private long groupId;
}
