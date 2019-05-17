package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class RequestDecisionRequest {

    private String flag;
    private long userId;
    private long groupId;
}
