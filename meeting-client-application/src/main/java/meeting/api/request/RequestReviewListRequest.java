package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class RequestReviewListRequest {

    private String flag;
    private long leaderId;
}
