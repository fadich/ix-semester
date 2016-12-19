<?php

namespace app\models\cashbox;

use app\models\logs\Logginer;
use app\models\logs\TotalLogger;
use app\models\Notification;
use Yii;

/**
 * Class CashBox
 * @package app\models\cashbox
 *
 * Class for working with cafes cashbox (when cash payment).
 *
 * @author Fadi Ahmad
 */
class CashBox extends BaseCashBox
{
    const CASH_BOX_TYPE = "cashbox";
    const DEFAULT_URL   = '/company/cash-box';

    /**
     * Method may returns CASH_BOX_TYPE
     *
     * @return string
     */
    public function getType() : string 
    {
        return self::CASH_BOX_TYPE;
    }

    /**
     * Log action (deposit or withdrawal) to cashbox (or cashboxes history/log).
     *
     * @param string $actionType deposit or withdrawal
     * @param float  $value      value of deposit or withdrawal
     * @param string $comment    actions interpretation
     */
    protected function logAction(string $actionType, float $value, string $comment)
    {
        $info = array(
            'type'    => self::CASH_BOX_TYPE,
            'value'   => $value,
            'comment' => str_replace(array("\r\n", "\r", "\n"), "<br />", $comment)
        );
        if($actionType == 'deposit') {
            Notification::setNotification(4, TotalLogger::CASHBOX, TotalLogger::ADDED, json_encode($info, JSON_UNESCAPED_UNICODE));
        } else {
            Notification::setNotification(4, TotalLogger::CASHBOX, TotalLogger::DELETED, json_encode($info, JSON_UNESCAPED_UNICODE));
        }
    }

    /**
     * Log any exception.
     *
     * @param \Throwable $e
     */
    protected function logError(\Throwable $e)
    {
        Logginer::logException($e);
    }
}
