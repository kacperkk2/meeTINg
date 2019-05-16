package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class EventListRequest {

    private String flag;

    private long groupId;
}
