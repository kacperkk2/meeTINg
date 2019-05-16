package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class NewGroupRequest {

    private String flag;

    private long leaderId;

    private String groupName;
}
