package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class NewEventRequest {

    private String flag;

    private long groupId;

    private String eventName;
}
