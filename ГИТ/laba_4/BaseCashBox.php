<?php

namespace app\models\cashbox;

use Yii;
use yii\base\Model;
use yii\db\Exception;
use yii\web\IdentityInterface;

/**
 * Class BaseCashBox.
 *
 * @package app\models\cashbox
 *
 * Cashbox using for counting and saving cash (or non-cash, in the case of non-cash payment)
 *  at the cafes (or, maybe, user's deposit, etc.) register (till, ticket window etc.).
 * Every cashbox can be deposited or withdrawal.
 * So, any operation with it (usually) includes one of this base action.
 *
 * There should be specified const CASH_BOX_TYPE in children classes,
 *  in which will be defined the type of the cashbox, for handy call to the database to the required field.
 *
 *
 * @property float  $value      (value of inserting or getting cash)
 * @property string $comment    (comment to operation)
 * @property int    $invoiceId  (ID of payment invoice, if there is produced payment of purchase)
 * @property float  $cash       (amount of cashboxes cash (money), read-only property)
 * @property string $type       (cashboxes type, that should be defined in children classes, read-only property)
 *
 * @author Fadi Ahmad
 */
abstract class BaseCashBox extends Model
{
    const ACTION_WITHDRAWAL = 'withdrawal';
    const ACTION_DEPOSIT    = 'deposit';

    /** @var int */
    public $invoiceId = 0;
    /** @var string */
    public $comment;
    /** @var float */
    public $value = 0;

    /** @var float */
    protected $_cash;
    /** @var int */
    protected $_cashBoxId;
    /** @var \yii\db\Connection */
    protected $_db;
    /** @var \yii\db\Connection */
    protected $_clientDb;

    /**
     * BaseCashBox constructor.
     *
     * @param int $cashBoxId
     */
    public function __construct(int $cashBoxId)
    {
        if ($cashBoxId < 1) {
            throw new \InvalidArgumentException("Incorrect cashboxes ID ({$cashBoxId})");
        }
        $this->_db        = &\Yii::$app->db;
        $this->_clientDb  = &\Yii::$app->clientDb;
        $this->_cashBoxId = $cashBoxId;
        $this->_cash      = $this->cash;
        parent::__construct();
    }

    /**
     * Name of the cashboxes table.
     *
     * @return string
     */
    public static function tableName() : string
    {
        return "{{%company_domain}}";
    }

    /**
     * Name of the cashboxes identity column in database.
     *
     * @return string
     */
    public static function cashBoxIdentity() : string
    {
        return "domain_id";
    }

    /**
     * As mentioned above, there is listed cashboxes base actions into scenarios: deposit and withdrawal.
     *
     * @return array
     */
    public function scenarios()
    {

        return [
            'deposit'    => ['value', 'invoiceId', 'comment'],
            'withdrawal' => ['value', 'comment'],
        ];
    }

    /**
     * Validation of input data (value (inserting or getting cash-value), comment and invoiceId).
     * 
     * Value can not be negative and if getting cash, it can not be more than cash of the cashbox.
     * 
     * Attributes (value and comment) are required, unless there is produced payment of purchase.
     * In this case, there should be Invoices ID and can be no comment
     *   (it's defined into definePaymentComment() method).
     *
     * @return array
     */
    public function rules()
    {
        return [
            [
                ['value'], 'required',
                'message' => 'Укажите сумму для проведения операции',
                'on'      => ['withdrawal', 'deposit'],
            ],
            [
                ['value'], 'double',
                'min'      => 0.01,
                'max'      => 9999999999,
                'tooSmall' => 'Значение должно быть больше 0.01',
                'tooBig'   => 'Неверое значение суммы',
                'on'       => ['deposit'],
            ],
            [
                ['value'], 'double',
                'min'      => 0.01,
                'max'      => $this->cash,
                'tooSmall' => 'Значение должно быть больше 0.01',
                'tooBig'   => "Значение суммы не должно превышать {$this->cash}",
                'on'       => ['withdrawal'],
            ],
            [
                ['comment'], 'required',
                'when'    => function() { return !$this->invoiceId; },
                'message' => 'Необходимо ввести комментарий',
                'on'      => ['withdrawal', 'deposit'],
            ],
            [
                ['comment'], 'filter',
                'filter' => 'trim',
                'on'     => ['withdrawal', 'deposit'],
            ],
            [
                ['comment'], 'string',
                'min'      => 3,
                'max'      => 155,
                'tooShort' => 'Введите, пожалуйста, более 2-х символов',
                'tooLong'  => 'Введите, пожалуйста, менее 156-и символов',
                'on'       => ['withdrawal', 'deposit'],
            ],
            [
                ['comment'], 'match',
                'pattern' => '/^[a-zA-Zа-яА-Я0-9 ёЁЇїІіЄєҐґ\+(\)\.\,\'\"\=\!\@\#\№\$\%\&\*\~\;\-\s\:\—\^\|\[\]\+]+$/ui',
                'message' => 'Поле содержит недопустимые символы',
                'on'      => ['withdrawal', 'deposit'],
            ],
            [
                ['invoiceId'], 'required',
                'message' => 'Укажите номер чека',
                'on'      => ['deposit'],
            ],
            [
                ['invoiceId'], 'integer',
                'min'      => 0,
                'max'      => 999999999,
                'tooSmall' => 'Неверый номер чека',
                'tooBig'   => 'Неверый номер чека',
                'on'       => ['deposit'],
            ],
        ];
    }

    /**
     * Returns cash-value (when call $cash property).
     *
     * @return float
     */
    public function getCash() : float
    {
        return $this->_cash ? $this->_cash : $this->getCashBoxesCash();
    }

    /**
     * Add cash (money, payment) to cashbox.
     * Value should be more than 0.
     *
     * @param array             $attributes  Loaded attributes
     *
     * @return bool
     * @throws \InvalidArgumentException
     */
    public function deposit(array $attributes) : bool
    {
        $this->scenario   = "deposit";
        $this->attributes = $attributes;
        if (!$this->validate()) {
            return false;
        }
        $transaction = $this->_db->beginTransaction();
        try {
            $this->insert($this->_cash + $this->value);
            if ($this->invoiceId) {
                $this->invoicesPayment();
            } else {
                $this->logAction(self::ACTION_DEPOSIT, $this->value, $this->comment);
            }
        } catch (Exception $e) {
            $transaction->rollBack();
            $this->logError($e);
            return false;
        }
        $transaction->commit();
        $this->_cash += $this->value;
        return true;
    }

    /**
     * Get cash (money, payment) from cashbox.
     * Value should be more than 0 and less than $this->_cash (cashboxes cash).
     * If user withdraws cash, he or she should indicate the reason.
     * 
     * @param array             $attributes  Loaded attributes
     *
     * @return bool
     */
    public function withdrawal(array $attributes) : bool
    {
        $this->scenario   = "withdrawal";
        $this->attributes = $attributes;
        if (!$this->validate()) {
            return false;
        }
        $transaction = $this->_db->beginTransaction();
        try {
            $this->insert($this->_cash - $this->value);
            $this->logAction(self::ACTION_WITHDRAWAL, $this->value, $this->comment);
        } catch (Exception $e) {
            $transaction->rollBack();
            $this->logError($e);
            return false;
        }
        $transaction->commit();
        $this->_cash -= $this->value;
        return true;
    }

    /**
     * Method may returns CASH_BOX_TYPE
     *
     * @return string
     */
    abstract public function getType() : string;

    /**
     * Create invoices payment log.
     *
     * Using $value and $invoiceId properties.
     */
    protected function invoicesPayment()
    {
        $this->logAction(self::ACTION_DEPOSIT, $this->value, $this->paymentComment());
    }

    /**
     * Payment's comment.
     * It defined separately to be able to override.
     *
     * @return string
     */
    protected function paymentComment() : string
    {
        return "Оплата чека №{$this->invoiceId}.";
    }

    /**
     * Getting cashboxes (cash form identified cashbox) cash for cashboxes type.
     *
     * @return float
     */
    protected function getCashBoxesCash() : float
    {
        try {
            return (float)$this->_db->createCommand("SELECT {$this->type} FROM " . self::tableName() . " WHERE " . self::cashBoxIdentity() . " = {$this->_cashBoxId}")->queryScalar();
        } catch (Exception $e) {
            return false;
        }
    }

    /**
     * Build SQL-request and update cashboxes cash.
     *
     * @param float $cash
     *
     * @return bool
     */
    protected function insert(float $cash) : bool
    {
        return (bool)$this->_db->createCommand()->update(self::tableName(), [$this->type => $cash], self::cashBoxIdentity() . " = {$this->_cashBoxId}")->execute();
    }

    /**
     * Log action (deposit or withdrawal) to cashbox (or cashboxes history/log).
     *
     * @param string $actionType deposit or withdrawal
     * @param float  $value      value of deposit or withdrawal
     * @param string $comment    actions interpretation
     */
    abstract protected function logAction(string $actionType, float $value, string $comment);

    /**
     * Log any exception.
     *
     * @param \Throwable $e
     */
    abstract protected function logError(\Throwable $e);
}
