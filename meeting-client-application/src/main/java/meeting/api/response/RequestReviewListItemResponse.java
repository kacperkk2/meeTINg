package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class RequestReviewListItemResponse {

    private long groupId;

    private String groupName;

    private String userName;

    private long userId;
}
