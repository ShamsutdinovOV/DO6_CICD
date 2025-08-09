#!/bin/bash



URL="https://api.telegram.org/bot8101795636:AAGgQjvAoDuAsuHxR3cM54e2k9ajraSnn-A/sendMessage"
if [ "$CI_JOB_STATUS" == "success" ]; then
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG+%0AStatus: SUCCESS"
else
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG+%0AStatus: FAIL"
fi
curl -s $TIME -d "chat_id=-1002848126113&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
